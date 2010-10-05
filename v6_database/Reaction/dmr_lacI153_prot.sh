file = [dmr_lacI153_prot.xml]

MoDeL
{
	reaction id = [dmr_lacI153_prot], name = [dimerization lacI], reversible = [true], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[dimerization of lacI];
		}
		listOfCompartments
		{
			compartment
			{
				compartmentReference:[Flask];
				currentCompartmentLabel:[Flask];
				parentCompartmentLabel:[ROOT];
			}
			compartment
			{
				compartmentReference:[E_coli];
				currentCompartmentLabel:[E_coli];
				parentCompartmentLabel:[Flask];
			}
		}
		listOfReactants
		{
			reactant	
			{
				speciesReference:[lacI153_prot];
				speciesLabel:[lacI153_prot_0];
				compartmentLabel:[E_coli];
			}
			reactant	
			{
				speciesReference:[lacI153_prot];
				speciesLabel:[lacI153_prot_1];
				compartmentLabel:[E_coli];
			}
		}
		listOfModifiers
		{
		}
		listOfProducts
		{
			product
			{
				speciesReference:[lacI153_dimer];
				speciesLabel:[lacI153_dimer];
				compartmentLabel:[E_coli];
			}
		}
		listOfSubstituentTransfers
		{
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_prot_0];
				to:[X0] speciesLabel = [lacI153_dimer];
			}
			substituentTransfer
			{
				from:[X1] speciesLabel = [lacI153_prot_0];
				to:[X1] speciesLabel = [lacI153_dimer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_prot_1];
				to:[X2] speciesLabel = [lacI153_dimer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_prot_1];
				to:[X3] speciesLabel = [lacI153_dimer];
			}
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math:[kon*lacI153_prot_0*lacI153_prot_1*E_coli];
				listOfLocalParameters
				{
					localParameter
					{
						id:[kon];
						name:[rate of binding];
						value:[1000000000];
						units:[litre_per_mole_per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
				}
				listOfConstraints
				{
				}
			}
			reverseKineticLaw
			{
				math:[koff*lacI153_dimer*E_coli];
				listOfLocalparameters
				{
					localParameter
					{
						id:[koff];
						name:[rate_of_unbinding];
						value:[10];
						units:[per_second];
						constant:[true];
					}
				}
				listOfReferencedParameters
				{
				}
				listOfConstraints
				{
				}
			}
		}
	}
}
