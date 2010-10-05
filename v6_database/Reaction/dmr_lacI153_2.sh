file = [dmr_lacI153_2.xml]

MoDeL
{
	reaction id = [dmr_lacI153_2], name = [dimerization lacI2], reversible = [true], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[dimerization of lacI2];
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
				speciesReference:[lacI153_dimer];
				speciesLabel:[lacI153_dimer_0];
				compartmentLabel:[E_coli];
			}
			reactant	
			{
				speciesReference:[lacI153_dimer];
				speciesLabel:[lacI153_dimer_1];
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
				speciesReference:[lacI153_tetramer];
				speciesLabel:[lacI153_tetramer];
				compartmentLabel:[E_coli];
			}
		}
		listOfSubstituentTransfers
		{
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_dimer_0];
				to:[X0] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X1] speciesLabel = [lacI153_dimer_0];
				to:[X1] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X2] speciesLabel = [lacI153_dimer_0];
				to:[X2] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X3] speciesLabel = [lacI153_dimer_0];
				to:[X3] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_dimer_1];
				to:[X4] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_dimer_1];
				to:[X5] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_dimer_1];
				to:[X6] speciesLabel = [lacI153_tetramer];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_dimer_1];
				to:[X7] speciesLabel = [lacI153_tetramer];
			}
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math:[kon*lacI153_dimer_0*lacI153_dimer_1*E_coli];
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
				math:[koff*lacI153_tetramer*E_coli];
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
