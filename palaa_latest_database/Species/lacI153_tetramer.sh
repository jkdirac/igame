file = [lacI153_tetramer.xml]

MoDeL
{
	species id = [lacI153_tetramer], name = [lacI153 tetramer]
	{
		interface
		{
			url:[http://2010.igem.org/Team:USTC_Software];
			shortDesc:[lacI153 tetramer];
		}
		cnModel
		{
			listOfChains
			{
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X0];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_0];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X1];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X2];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_1];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X3];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X4];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_2];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X5];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
				chain
				{
					listOfParts
					{
						part
						{
							partReference:[ANY];
							partLabel:[X6];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
						part
						{
							partReference:[lacI153];
							partLabel:[lacI_3];
							partType:[ForwardProtein];
							partCategory:[biobrick];
						}
						part
						{
							partReference:[ANY];
							partLabel:[X7];
							partType:[ForwardProtein];
							partCategory:[substituent];
						}
					}
				}
			}
			listOfTrees
			{
				tree
				{
					listOfNodes
					{
						node
						{
							currentNodeLabel:[lacI_0];
							parentNodeLabel:[lacI2_0];
						}
						node
						{
							currentNodeLabel:[lacI_1];
							parentNodeLabel:[lacI2_0];
						}
						node
						{
							currentNodeLabel:[lacI_2];
							parentNodeLabel:[lacI2_1];
						}
						node
						{
							currentNodeLabel:[lacI_3];
							parentNodeLabel:[lacI2_1];
						}
						node
						{
							currentNodeLabel:[lacI2_0];
							parentNodeLabel:[lacI4];
						}
						node
						{
							currentNodeLabel:[lacI2_1];
							parentNodeLabel:[lacI4];
						}
						node
						{
							currentNodeLabel:[lacI4];
							parentNodeLabel:[ROOT];
						}
					}
				}
			}
		}
		listOfReferencedReactions
		{
			referencedReaction:[bid_placI185_lacI153_4] speciesType = [reactant];
		}
	}
}
