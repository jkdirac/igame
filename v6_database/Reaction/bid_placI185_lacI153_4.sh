file = [bid_placI185_lacI153_4.xml]

MoDeL
{
	reaction id = [bid_placI185_lacI153_4], name = [binding placI:lacI4], reversible = [true], fast = [false]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			short_desc:[binding of placI185_dna and lacI153_tetramer];
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
				speciesReference:[placI185_dna];
				speciesLabel:[placI185_dna];
				compartmentLabel:[E_coli] itself = [];
			}
			reactant
			{
				speciesReference:[lacI153_tetramer];
				speciesLabel:[lacI153_tetramer];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfModifiers
		{
		}
		listOfProducts
		{
			product
			{
				speciesReference:[placI185lacI153_4];
				speciesLabel:[placI185lacI153_4];
				compartmentLabel:[E_coli] itself = [];
			}
		}
		listOfSubstituentTransfers
		{
			substituentTransfer
			{
				from:[X0] speciesLabel = [placI185_dna];
				to:[X0] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X1] speciesLabel = [placI185_dna];
				to:[X1] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X0] speciesLabel = [lacI153_tetramer];
				to:[X2] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X1] speciesLabel = [lacI153_tetramer];
				to:[X3] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X2] speciesLabel = [lacI153_tetramer];
				to:[X4] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X3] speciesLabel = [lacI153_tetramer];
				to:[X5] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X4] speciesLabel = [lacI153_tetramer];
				to:[X6] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X5] speciesLabel = [lacI153_tetramer];
				to:[X7] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X6] speciesLabel = [lacI153_tetramer];
				to:[X8] speciesLabel = [placI185lacI153_4];
			}
			substituentTransfer
			{
				from:[X7] speciesLabel = [lacI153_tetramer];
				to:[X9] speciesLabel = [placI185lacI153_4];
			}
		}
		kineticLaw
		{
			forwardKineticlaw
			{
				math
				{
					apply
					{
						times
						{
						}
						ci:[placI185_dna];
						ci:[lacI153_tetramer];
						ci:[kon];
						ci:[E_coli];
					}
				}
				listOfLocalParameters
				{
					localParameter
					{
						id:[kon];
						name:[rate_of_binding];
						value:[2000000000];
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
				math
				{
					times
					{
					}
					ci:[placI185lacI153_4];
					ci:[koff];
					ci:[E_coli];
				}
				listOfLocalparameters
				{
					localParameter
					{
						id:[koff];
						name:[rate_of_unbinding];
						value:[0.04];
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
